#include <iostream>
#include <string>
#include <set>

class Message
{
	friend class Folder;
public:
	explicit Message(const std::string &str = ""): contents() { }
	Message(const Message&);
	Message operator=(const Message&);
	~Message();
	void save(Folder&);
	void remove(Folder&);
private:
	std::string contents;
	std::set<Folder*> folders;
	void addToFolders(const Message&);
	void removeFromFolders();
};

void Message::save(Folder &f)
{
	folders.insert(&f);
	f.addMsg(this);
}
void Message::remove(Folder &f)
{
	folders.erase(&f);
	f.remMsg(this);
}

void Message::addToFolders(const Message &m)
{
	for(auto f : m.folders)
		f->addMsg(this);
}

Message::Message(const Message &m): contents(m.contents), folders(m.folders)
{
	addToFolders(m);
}

void Message::removeFromFolders()
{
	for(auto f : folders)
		f->remMsg(this);
}

Message::~Message()
{
	removeFromFolders();
}

Message& Message::operator=(const Message &rhs)
{
	removeFromFolders();
	contents = rhs.contents;
	folders = rhs.folders;
	addToFolders(rhs);
	return(*this);
}

void swap(Message *lhs, Message *rhs)
{
	using std::swap;

	for(auto f : lhs->folders)
		f->remMsg(&lhs);
	for(auto f : rhs->folders)
		f->remMsg(&rhs);

	swap(lhs->folders, rhs->folders);
	swap(lhs->contents, rhs->contents);

	for(auto f : lhs->folders)
		f->addMsg(&lhs);
	for(auto f : rhs->folders)
		f->addMsg(&rhs);
}

int main()
{
	return(0);
}

