#include <vector>
#include "indri/QueryEnvironment.hpp"
#include "lemur/Exception.hpp"

using namespace indri::api;

void tryAddServer(QueryEnvironment *env, string server) {
  try {
    env->addServer(server);
  } catch (lemur::api::Exception &e) {
    cout << "Failed to add: " << server << endl;
  }
}

std::vector<string> urls(QueryEnvironment *env, string query) {
  std::vector<ScoredExtentResult> results = env->runQuery(query, 1);
  return env->documentMetadata(results, "url");
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

  std::vector<string> us = urls(&env, argv[1]);

  for (int i = 0; i < us.size(); i++) {
    cout << us.at(i) << endl;
  }
}
