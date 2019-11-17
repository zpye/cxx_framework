#include <iostream>
#include <string>
#include <vector>

#include "SimpleIni.h"

int main(int argc, char* argv[]) {
  CSimpleIni ini;
  ini.SetMultiKey(true);
  ini.LoadFile("test.ini");

  CSimpleIni::TNamesDepend values;
  ini.GetAllValues("section", "str1", values);

  double num = ini.GetDoubleValue("section2", "number", 0.0);

  ini.SetValue("section", "str1", "mystr1", nullptr, true);
  ini.SetValue("section", "str1", "mystr2");
  ini.SetValue("section", "str1", "mystr3");
  ini.SetValue("section", "str2", "string", "; string comment", true);
  ini.SetDoubleValue("section2", "number", 1.23, nullptr, true);
  ini.SaveFile("test.ini");
 
  return 0;
}