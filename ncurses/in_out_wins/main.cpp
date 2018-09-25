#include <cstring>
#include <ctime>

#include <array>
#include <chrono>
#include <iostream>
#include <list>
#include <memory>
#include <queue>
#include <string>

#include <mutex>
#include <thread>

#include <ncurses.h>

#define DELAY 1000

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
	char      buffer[param.width - 2];
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

		mvwgetnstr(win, input_line, 1, mesBuffer, mesBufferSize);
		cleanWin(win, bottom_line, top_line, win_p);

		save_current_time(timeBuffer, timeBufferSize);
		snprintf(buffer, bufferSize, "%s >> %s", timeBuffer, mesBuffer);

		inputQueue->push((str_ptr) new std::string(buffer));

		wrefresh(win);
	}
}

void show_output(WINDOW *win, win_param win_p) {
	const int top_line = 3, bottom_line = win_p.height - top_line;
	while (PROG_RUN) {
		if (inputQueue->empty()) continue;

		int     output_line  = win_p.height - 2;
		str_ptr new_mes      = inputQueue->front();
		size_t  dispMesCount = 0;

		cleanWin(win, bottom_line, top_line, win_p);

		if (!dispInputs->empty()) dispMesCount = dispInputs->size();

		mvwaddnstr(win, output_line, 1, new_mes->c_str(), new_mes->length());

		mtx.lock();
		for (str_ptr &s : *dispInputs)
			mvwaddnstr(win, --output_line, 1, s->c_str(), s->length());
		mtx.unlock();

		if (dispMesCount >= static_cast<size_t>(bottom_line))
			dispInputs->pop_front();

		dispInputs->push_back(new_mes);
		inputQueue->pop();

		wrefresh(win);

		std::this_thread::sleep_for(std::chrono::milliseconds(DELAY));
	}
}

std::array<std::thread, 2> define_threads(WINDOW *in, WINDOW *out,
                                          win_param in_p, win_param out_p) {
	std::array<std::thread, 2> ths;
	std::thread                input(get_user_input, in, in_p);
	std::thread                output(show_output, out, out_p);
	ths.at(0) = (std::move(input));
	ths.at(1) = (std::move(output));
	return ths;
}

void prog() {
	win_param output_win, input_win;
	define_params(output_win, input_win);

	WINDOW *prog_in  = create_new_win(input_win);
	WINDOW *prog_out = create_new_win(output_win);

	std::array<std::thread, 2> threads =
	    define_threads(prog_in, prog_out, input_win, output_win);

	for (std::thread &th : threads)
		if (th.joinable()) th.join();
}

int main() {
	initscr();

	prog();

	endwin();

	return 0;
}
