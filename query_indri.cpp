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

  string servers[10] = { "10.1.1.236:12000",
                         "10.1.1.236:12001",
                         "10.1.1.236:12002",
                         "10.1.1.236:12003",
                         "10.1.1.236:12004",
                         "10.1.1.239:12005",
                         "10.1.1.239:12006",
                         "10.1.1.239:12007",
                         "10.1.1.239:12008",
                         "10.1.1.239:12009",
                         "10.1.1.227:12010",
                         "10.1.1.227:12011",
                         "10.1.1.227:12012",
                         "10.1.1.227:12013",
                         "10.1.1.227:12014",
                         "10.1.1.228:12015",
                         "10.1.1.228:12016",
                         "10.1.1.228:12017",
                         "10.1.1.228:12018",
                         "10.1.1.228:12019" };

  for (int i = 0; i < 10; i++) {
    tryAddServer(&env, servers[i]);
  }

  string filename = argv[1];
  
  readQueriesFile(&env, filename);
}
