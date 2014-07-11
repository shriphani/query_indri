#include <fstream>
#include <vector>
#include "indri/QueryEnvironment.hpp"
#include "lemur/Exception.hpp"

using namespace indri::api;

void tryAddServer(QueryEnvironment *env, string server) {
  try {
    env->addServer(server);
  } catch (lemur::api::Exception &e) {
    cerr << "Failed to add: " << server << endl;
  }
}

string urls(QueryEnvironment *env, string query) {
  // empty queries are pointless
  if(query.empty() || query == "#1()") {
    return "--";
  }

  std::vector<ScoredExtentResult> results = env->runQuery(query, 1);

  if (results.size() > 0) {
    return env->documentMetadata(results, "url").at(0);
  } else {
    return "--";
  }
}

int readQueriesFile(QueryEnvironment *env, string queries_file) {
  std::ifstream infile(queries_file.c_str());

  std::string line;
  
  while (std::getline(infile, line)) {
    string query =  "#1(" + line + ")";
    cout << urls(env, query) << endl;
  }
}

int main(int argc, char *argv[]) {

  // assuming that the first argument is the query

  QueryEnvironment env;

  string servers[10] = { "10.1.1.246:9001",
                         "10.1.1.246:9002",
                         "10.1.1.246:9003",
                         "10.1.1.246:9004",
                         "10.1.1.246:9005",
                         "10.1.1.246:9006",
                         "10.1.1.246:9007",
                         "10.1.1.246:9008",
                         "10.1.1.246:9009",
                         "10.1.1.246:9010" };

  for (int i = 0; i < 10; i++) {
    tryAddServer(&env, servers[i]);
  }

  string filename = argv[1];
  
  readQueriesFile(&env, filename);
}
