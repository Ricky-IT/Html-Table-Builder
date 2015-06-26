#include "Tag.h"
using namespace std;

Tag::Tag(std::string val, char ty)
   :value(val), type(ty)
{

}


Tag::~Tag()
{
}


void Tag::push(char item) //aggiunge il carattere al valore
{
	value += item;
}

