#include "Element.h"
using namespace std;

Element::Element(std::string val, char t)
   :value(val), type(t)
{

}

void Element::push(char item) //aggiunge il carattere al valore
{
	value += item;
}

void Element::cleardata()
{
	value = "";
}

