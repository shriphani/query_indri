#include <vector>
#include "indri/QueryEnvironment.hpp"

using namespace indri::api;

int main() {

  QueryEnvironment indriEnvironment;

  indriEnvironment.addServer("10.1.1.246:9001");

  std::vector<ScoredExtentResult> results = indriEnvironment.runQuery("#1(barack obama)", 5);

  std::vector<int> docIds;

  std::vector<std::string> urls = indriEnvironment.documentMetadata(results, "url");

  for (std::vector<std::string>::iterator it = urls.begin(); it != urls.end(); ++it) {
    cout << *it << endl;
  }

}
