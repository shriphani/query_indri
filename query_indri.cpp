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

  
}
