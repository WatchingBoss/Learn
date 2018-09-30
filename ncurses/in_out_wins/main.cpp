#include <cstring>
#include <ctime>

#include <array>
#include <list>
#include <queue>

#include <chrono>
#include <iostream>
#include <memory>
#include <string>

#include <mutex>
#include <thread>

#include <ncurses.h>

#define DELAY 1000

#define USE_COLOR(win, pair, x)                                                \
	wattron(win, COLOR_PAIR(pair));                                            \
	x;                                                                         \
	wattroff(win, COLOR_PAIR(pair))

using str_ptr   = std::shared_ptr<std::string>;
using str_q_ptr = std::shared_ptr<std::queue<str_ptr>>;
using str_l_ptr = std::shared_ptr<std::list<str_ptr>>;

str_q_ptr inputQueue(new std::queue<str_ptr>);
str_l_ptr dispInputs(new std::list<str_ptr>);

struct win_param {
	int height, width, starty, startx;
};

static bool PROG_RUN = true;

void sys_er(const char *er) {
	perror(er);
	exit(EXIT_FAILURE);
}

void define_params(win_param &output_win, win_param &input_win) {
	output_win.height = static_cast<int>(static_cast<float>(LINES) * 0.9f);
	output_win.width  = COLS - 2;
	output_win.starty = 1;
	output_win.startx = 1;

	input_win.height = static_cast<int>(static_cast<float>(LINES) * 0.1f);
	input_win.width  = COLS - 2;
	input_win.starty = output_win.height;
	input_win.startx = 1;
}

WINDOW *create_new_win(win_param &param) {
	WINDOW *win = newwin(param.height, param.width, param.starty, param.startx);
	if (!win) sys_er("Cannot create new win!");
	box(win, 0, 0);
	wrefresh(win);
	return win;
}

void cleanWin(WINDOW *win, int bottom, int top, const win_param &param) {
	const int bufferSize = param.width - 2;
	char      buffer[bufferSize];
	memset(buffer, ' ', bufferSize);
	for (int i = bottom; i >= top; --i)
		mvwaddnstr(win, i, 1, buffer, bufferSize);
}

void save_current_time(char buffer[], size_t bufferSize) {
	time_t     curTime  = 0;
	struct tm *formTime = NULL;

	time(&curTime);
	formTime = localtime(&curTime);
	strftime(buffer, bufferSize, "%H:%M:%S", formTime);
}

std::mutex mtx;

void get_user_input(WINDOW *win, win_param win_p) {
	const int top_line = 1, bottom_line = win_p.height - 2,
	          input_line = win_p.height - 4;

	constexpr size_t mesBufferSize = 1024, timeBufferSize = 20,
	                 bufferSize = mesBufferSize + timeBufferSize;
	while (PROG_RUN) {
		char mesBuffer[mesBufferSize]   = { 0 },
		     timeBuffer[timeBufferSize] = { 0 }, buffer[bufferSize] = { 0 };

		mtx.lock();
		mvwgetnstr(win, input_line, 1, mesBuffer, mesBufferSize);
		mtx.unlock();

		cleanWin(win, bottom_line, top_line, win_p);

		save_current_time(timeBuffer, timeBufferSize);
		snprintf(buffer, bufferSize, "%s >> %s", timeBuffer, mesBuffer);

		inputQueue->push((str_ptr) new std::string(buffer));

		wrefresh(win);
	}
}

void show_output(WINDOW *win, win_param win_p) {
	const int height = win_p.height, top_line = 3, bottom_line = height - 2;
	while (PROG_RUN) {
		if (inputQueue->empty()) continue;

		int     output_line  = bottom_line;
		str_ptr new_mes      = inputQueue->front();
		size_t  dispMesCount = 0;

		cleanWin(win, bottom_line, top_line, win_p);

		if (!dispInputs->empty()) dispMesCount = dispInputs->size();

		USE_COLOR(win, 2,
		          mvwaddnstr(win, output_line, 1, new_mes->c_str(),
		                     new_mes->length()));

		USE_COLOR(win, 3,
		          for (const str_ptr &s
		               : *dispInputs) mvwaddnstr(win, --output_line, 1,
		                                         s->c_str(), s->length()));

		if (dispMesCount >= static_cast<size_t>(height - 5))
			dispInputs->pop_back();

		dispInputs->push_front(new_mes);
		inputQueue->pop();

		wrefresh(win);
	}
}

std::array<std::thread, 2> define_threads(WINDOW *in, WINDOW *out,
                                          win_param in_p, win_param out_p) {
	std::thread input(get_user_input, in, in_p);
	std::thread output(show_output, out, out_p);

	std::array<std::thread, 2> ths = { std::move(input), std::move(output) };
	return ths;
}

void displayWinTitle(WINDOW *win, win_param &win_p)
{
	const char *title = "Display user inputs";
	const size_t titleSize = strlen(title);
	int x = win_p.width / 2 - titleSize / 2, y = 2;

	USE_COLOR(win, 1, mvwprintw(win, y, x, title, titleSize));

	wrefresh(win);
}

void prog() {
	initscr();
	start_color();
	init_pair(1, COLOR_CYAN, COLOR_BLACK);
	init_pair(2, COLOR_YELLOW, COLOR_BLACK);
	init_pair(3, COLOR_GREEN, COLOR_BLACK);

	win_param output_win, input_win;
	define_params(output_win, input_win);

	WINDOW *prog_in  = create_new_win(input_win);
	WINDOW *prog_out = create_new_win(output_win);

	displayWinTitle(prog_out, output_win);

	std::array<std::thread, 2> threads =
	    define_threads(prog_in, prog_out, input_win, output_win);

	for (std::thread &th : threads)
		if (th.joinable()) th.join();

	endwin();
}

void getUserName(){
	std::string userName;
	std::cout << "Enter your name: ";
	std::getline(std::cin, userName);
	str_ptr message(new std::string("Welcome " + userName + "!"));
	inputQueue->push(message);
}

int main() {
	getUserName();

	std::thread p(prog);

	if(p.joinable()) p.join();

	return 0;
}
