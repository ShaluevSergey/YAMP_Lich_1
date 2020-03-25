#include <iostream>
#include <Windows.h>
#include <string>
#include <fstream>
#include <cwctype>
#include <locale>

using namespace std;

class list
{
private:
	struct Node 
	{
		string msg;
		Node* previous = NULL;
		Node* next = NULL;
	};
	Node* root;
	Node* tail;
public:
	list()
	{
		root = tail = NULL;
	}
	~list()
	{
		while (root)
		{
			tail = root->next;
			delete root;
			root = tail;
		}
	}
	void addNext(string msg)
	{
		Node* new_node = new Node;
		new_node->next = NULL;
		new_node->msg = msg;
		if (!root)
		{
			new_node->previous = NULL;
			root = tail = new_node;
		}
		else
		{
			new_node->previous = tail;
			tail->next = new_node;
			tail = new_node;
		}
		return;
	}
	void showFromTail()
	{
		Node* tmp_node = tail;

		while (tmp_node)
		{
			cout << tmp_node->msg << endl;
			tmp_node = tmp_node->previous;
		}
		cout << endl;
		return;
	}
	void showFromRoot()
	{
		Node* tmp_node = root;

		while (tmp_node)
		{
			cout << tmp_node->msg << endl;
			tmp_node = tmp_node->next;
		}
		cout << endl;
		return;
	}
	void readFromFile(string fileName)
	{
		ifstream file(fileName); 

		string str;

		if (!file.is_open())
			cout << "Файл не может быть открыт!" << endl;
		else
		{
			while (!file.eof())
			{
				file >> str;
				addNext(str);
			}
			file.close();
		}
		return;
	}
	void countOneLetterWords()
	{
		Node* tmp_node = root;
		int counter = 0;
		
		while (tmp_node->next)
		{
			char f, s;
			f = tolower(tmp_node->msg[0], locale("rus"));
			s = tolower(tmp_node->next->msg[0], locale("rus"));
			if (f == s)
				counter++;
			tmp_node = tmp_node->next;
		}
		cout << "Количество слов, которые начинаются с той же буквы, что и следующее слово: " << counter << endl;
		return;
	}
};

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	list List;
	List.readFromFile("Words.txt");
	List.showFromRoot();
	List.countOneLetterWords();

	return 0;
}