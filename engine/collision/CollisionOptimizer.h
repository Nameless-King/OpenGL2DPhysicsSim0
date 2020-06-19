
#include <string>

class CollisionOptimizer{
struct Domain{
        Domain(string groupID):
            groupID(groupID),
            valueList(new std::vector<Object*>()),
            next(NULL)
        {}

        string groupID;
        std::vector<Object*>* valueList;
        Domain* next;
    };

private:
    Domain* m_front;
    Domain* m_postEnd;
    unsigned int m_totalGroups;
    unsigned int m_totalObjects;
public:
    CollisionOptimizer();
    void createCollisionGroup(const std::string& groupID);    
    void addObjectToGroup(const std::string& groupID, Object* object);
    std::vector<Object*>* getGroupValues(const std::string groupID);
    
};