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
		string msg;//поле данных
		Node* previous = NULL;//указатель на предыдущий элемент
		Node* next = NULL;//указатель на следующий элемент
	};
	Node* root;//первый элемент списка
	Node* tail;//последний элемент списка
public:
	list()//конструкор по умолчанию
	{
		root = tail = NULL;
	}
	~list()//деструктор
	{
		while (root)
		{
			tail = root->next;
			delete root;
			root = tail;
		}
	}
	void addNext(string msg)//добавление элемента в конец
	{
		Node* new_node = new Node;//создаём новый элемент
		new_node->next = NULL;//присваиваем ему адрес
		new_node->msg = msg;//присваиваем ему значение
		if (!root)//если список пустой
		{
			root = tail = new_node;//первый элемент будет и последним и будет равен новому элементу
		}
		else
		{
			new_node->previous = tail;//Т.к мы добавляем в конец, то указатель нового элемента должен указывать на прошлый хвост списка
			tail->next = new_node;//в прошлом хвосте меняем указатель на новый хвост
			tail = new_node;//старый хвост будет равен новому хвосту
		}
		return;
	}
	void showFromRoot()//выводим список с первого элемента
	{
		Node* tmp_node = root;//переменная для вывода

		while (tmp_node)//пока не NULL
		{
			cout << tmp_node->msg << endl;//обращаемся к поле данных msg и выводим
			tmp_node = tmp_node->next;//Указываем на следующий элемент
		}
		cout << endl;
		return;
	}
	void readFromFile(string fileName)//функция чтения из файла
	{
		ifstream file(fileName); //открываем файл

		string str;

		if (!file.is_open())//проверка открыт ли файл
			cout << "Файл не может быть открыт!" << endl;
		else
		{
			while (!file.eof())//пока файл не кончился
			{
				file >> str;//считываем всё из файла
				addNext(str);//добавляем в список через функцию
			}
			file.close();//закрываем файл
		}
		return;
	}
	void countOneLetterWords()//функция проверки слов
	{
		Node* tmp_node = root;//переменная для "перебора" слов
		int counter = 0;//счётчик
		
		while (tmp_node->next)//пока не конец списка
		{
			char f, s;//переменные для букв
			f = tolower(tmp_node->msg[0], locale("rus"));//запоминаем первую букву слова
			s = tolower(tmp_node->next->msg[0], locale("rus"));//запоминаем первую букву второго слова
			if (f == s)//если буквы равны
				counter++;//счётчик
			tmp_node = tmp_node->next;//следующее слово
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
	List.readFromFile("Words.txt");//чтение из файла
	List.showFromRoot();//показываем слова
	List.countOneLetterWords();//подсчёт слов

	return 0;
}