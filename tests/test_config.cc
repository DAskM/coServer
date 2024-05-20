#include "../src/config.h"
#include "../src/log.h"

#include <yaml-cpp/yaml.h>

coServer::ConfigVar<int>::ptr g_int_value_config = 
    coServer::Config::Lookup("system.port", (int)8080, "system port");

coServer::ConfigVar<float>::ptr g_float_value_config =
    coServer::Config::Lookup("system.value", (float)10.2f, "system value");

void print_yaml(const YAML::Node& node, int level){
    if(node.IsScalar()){
        COSERVER_LOG_INFO(COSERVER_LOG_ROOT()) << std::string(level*4, ' ')
            << node.Scalar() << " - " << node.Type() << " - " << level;
    }else if(node.IsMap()){ 
        for(auto it = node.begin(); it!=node.end(); it++){
            COSERVER_LOG_INFO(COSERVER_LOG_ROOT()) << std::string(level*4, ' ')
                << it->first << " - " << it->second.Type() << " - " << level;
            print_yaml(it->second, level+1);
        }
    }else if(node.IsNull()){
        COSERVER_LOG_INFO(COSERVER_LOG_ROOT()) << std::string(level*4, ' ')
            << "NULL - " << node.Type() << " - " << level;
    }else if(node.IsSequence()){
        for(size_t i=0; i<node.size(); i++){
            COSERVER_LOG_INFO(COSERVER_LOG_ROOT()) << std::string(level*4, ' ')
                << i << " - " << node[i].Type() << " - " << level;
            print_yaml(node[i], level+1);
        }
    }
}

void test_yaml(){
    YAML::Node root = YAML::LoadFile("/home/leedong/Desktop/Project/conServer/tests/logStd.yml");
    print_yaml(root, 0);
    COSERVER_LOG_INFO(COSERVER_LOG_ROOT()) << root.Scalar();
}

void test_config(){
    COSERVER_LOG_INFO(COSERVER_LOG_ROOT()) << "before: " << g_int_value_config->getValue();
    COSERVER_LOG_INFO(COSERVER_LOG_ROOT()) << "before: " << g_float_value_config->toString();
}

int main(int argc, char** argv){
    test_yaml();
    return 0;
}
