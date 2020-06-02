#include <vector>
#include <assert.h>
#include <sstream>

#include "token.h"

using namespace std;

void programKeywordOnlyIsInvalidProgram() {
  static string programText = "program";
  istringstream inputStream(programText.c_str());
  
  //  string errorMessage = parser.parse(inputStream, errorStream);

}

int main(int argc, char ** argv) {
  return 0;
}



