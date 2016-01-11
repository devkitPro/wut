#include <fstream>
#include <set>
#include <string>
#include <iostream>

int main(int argc, char **argv)
{
   std::set<std::string> funcExports, dataExports;
   std::string line;
   std::ifstream in;
   std::ofstream out;

   if (argc < 4) {
      std::cout << argv[0] << " <readrpl output> <exports.h> <output.txt>" << std::endl;
      return 0;
   }

   in.open(argv[1]);

   if (!in.is_open()) {
      std::cout << "Could not open file " << argv[1] << " for reading" << std::endl;
      return -1;
   }


   while (!in.eof()) {
      std::string strAddr, name;
      in >> strAddr >> name;

      auto addr = std::stoul(strAddr, nullptr, 16);

      if (addr >= 0x10000000) {
         dataExports.insert(name);
      } else {
         funcExports.insert(name);
      }
   }

   in.close();
   in.open(argv[2]);

   if (!in.is_open()) {
      std::cout << "Could not open file " << argv[2] << " for reading" << std::endl;
      return -1;
   }

   auto funcCount = funcExports.size();
   auto dataCount = funcExports.size();

   while (std::getline(in, line)) {
      if (line.find("EXPORT(") == 0) {
         auto name = line.substr(strlen("EXPORT("));
         name = name.erase(name.find(')'), 2);

         auto funcItr = funcExports.find(name);

         if (funcItr != funcExports.end()) {
            funcExports.erase(funcItr);
         }

         auto dataItr = dataExports.find(name);

         if (dataItr != dataExports.end()) {
            dataExports.erase(funcItr);
         }
      }
   }

   auto unimplFuncCount = funcExports.size();
   auto unimplDataCount = funcExports.size();

   out.open(argv[3]);

   if (!out.is_open()) {
      std::cout << "Could not open file " << argv[3] << " for writing" << std::endl;
      return -1;
   }

   if (funcExports.size()) {
      out << "Unimplemented function exports " << unimplFuncCount << "/" << funcCount << ":" << std::endl;

      for (auto &name : funcExports) {
         out << name << std::endl;
      }

      out << std::endl;
   }

   if (dataExports.size()) {
      out << "Unimplemented data exports " << unimplDataCount << "/" << dataCount << ":" << std::endl;

      for (auto &name : dataExports) {
         out << name << std::endl;
      }

      out << std::endl;
   }

   return 0;
}
