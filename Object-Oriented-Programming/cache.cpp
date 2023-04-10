#include <iostream>
#include <chrono>

#include <thread>
# include <map>

/* * @file: lsp.cpp
* @brief: Liskov Substitution Principle, LSP С++

* @developer: @ynwqmv
* @license: GNU General Public License 2.0
*/




// Singleton Pattern
class Cache
{
    static Cache* instance; // the only one private instance
    std::map<std::string, std::string> cacheMap; // cache container
public:
    
    static Cache* getInstance() { /* getter for our instance */
        if (!instance)
        {
            instance = new Cache();
        }
        return instance;
    }
    void pushData(const std::string& key, const std::string& value)
    {
        cacheMap[key] = value;
    }


    std::string getData(const std::string& key) {
        if (cacheMap.count(key))
        {
            return cacheMap[key];
        }
        return {};
    }

   
    
    void clearCache()
    {
        cacheMap.clear();
    }
};
Cache* Cache::instance = nullptr;

int main() {
    using namespace std;
 
    Cache* cache = Cache::getInstance();
    cache->pushData("key1", "apple");
    cout << cache->getData("key1") << endl;
    cache->clearCache();
    std::cout << endl << cache << '\n';
    delete cache;
    cache = nullptr;
    std::cout << endl << cache << '\n';
    return 0;

}
