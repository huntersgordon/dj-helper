#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <fstream>
#include <string>
using namespace std;

void replaceAll(std::string& source, const std::string& from, const std::string& to)
     {
         std::string newString;
         newString.reserve(source.length());  // avoids a few memory allocations

         std::string::size_type lastPos = 0;
         std::string::size_type findPos;

         while(std::string::npos != (findPos = source.find(from, lastPos)))
         {
             newString.append(source, lastPos, findPos - lastPos);
             newString += to;
             lastPos = findPos + from.length();
         }

         // Care for the rest after last occurrence
         newString += source.substr(lastPos);

         source.swap(newString);
}



std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
    if (!pipe) throw std::runtime_error("popen() failed!");
    while (!feof(pipe.get())) {
        if (fgets(buffer.data(), 128, pipe.get()) != nullptr)
            result += buffer.data();
    }
    return result;
}

int main(){

     //string total = "";
     string line;
     string mystring;
     string input;
     string output;
     string comm;
     string custom;
     string links[100] = {};
     int choice;
     int sum = 74000;
     string query = "";
     int firstoccurence;
     // ifstream myfile ("done.txt");
     // if (myfile.is_open())

        while ( true )
        {
          a:

          if (input == "q"){
               //cout<<output;
               exit (EXIT_FAILURE);
               //cout<<"meow";
          }


               cout<< "custom song or link: ";
               //cin.clear();
               cin.ignore(numeric_limits<streamsize>::max(), '\n');
               getline(cin,custom);
               line = custom;
               replaceAll(line, " ", "+");

          if (custom.find("youtube") != string::npos){
               comm = "youtube-dl --extract-audio --audio-format mp3 \"" + custom  +  "\"" ;
               cout<<"command was: "<<comm<<endl<<"---------------"<<endl;
               cout<< "trying to download " + custom +  "..." <<endl;
               exec(comm.c_str());
          }

          else if (input != "n"){


          replaceAll(line, " ", "+");
          line.erase(std::remove(line.begin(), line.end(), '\''), line.end());
          line.erase(std::remove(line.begin(), line.end(), '`'), line.end());
          line.erase(std::remove(line.begin(), line.end(), '\"'), line.end());
          line.erase(std::remove(line.begin(), line.end(), '('), line.end());
          line.erase(std::remove(line.begin(), line.end(), ')'), line.end());
          mystring = "curl https://www.youtube.com/results?search_query="+line + "+song";
          cout<<"curling: "+mystring<<endl;
          output = exec(mystring.c_str());
          for(int i = 0; i < 100; i++){
          if (i == 30) break;
          try{
          firstoccurence = output.find("\"  title=\"",sum);
          sum = firstoccurence + 10;
          //cout<<"its ok";

          //output = output.substr(sum);
          }catch(const std::exception& e){
               break;
          }


               string str = output.substr(firstoccurence+10,120);

               //cout<<output.substr(firstoccurence+10,800);
               if ((str.substr(0,str.find("rel"))).find("PE html") != std::string::npos) {
                    cout<<"-------------------"<<endl;

                    //user chooses number song they want to download.

                    break;
                    }
                    try{
               links[i] = string(output.substr(firstoccurence-210,50).substr((output.substr(firstoccurence-210,50).find("watch?v=") == std::string::npos? 0:output.substr(firstoccurence-210,50).find("watch?v=") ),19));
                    }catch(const std::exception& e){
                         break;
                    }
               //cout<<endl<<  output.substr(firstoccurence-210,50).substr(output.substr(firstoccurence-210,50).find("watch?v="),19)  <<endl;
               string gah = to_string(i) + ": " + str.substr(0,str.find("rel"));
               replaceAll(gah, "&#39;", "\'");
               replaceAll(gah, "&amp;", "&");
               replaceAll(gah, "&quot;", "\"");

               cout<<gah<<endl;

          }

          cout<< "select number to download: ";
          cin>> choice;
          if (choice != 69) {

          //remove quotes
          links[choice].erase(
               remove( links[choice].begin(), links[choice].end(), '\"' ),
               links[choice].end()
          );
          links[choice].erase(
               remove( links[choice].begin(), links[choice].end(), '\'' ),
               links[choice].end()
          );
          //get rid of anything after a space bar character
          links[choice] = links[choice].substr(0, links[choice].find(" "));


          comm = "youtube-dl --extract-audio --audio-format mp3 \"https://www.youtube.com/"+ links[choice] + "\"" ;
          cout<<"command was: "<<comm<<endl;



          cout<< "trying to download youtube.com/" + links[choice] + "..." <<endl;
          exec(comm.c_str());
          }
          goto a;

               //exit (EXIT_FAILURE);
               //cout<<output;
               //total = total + line + '\n';
          }
             }




     // cout<<total;

      return 0;


}
