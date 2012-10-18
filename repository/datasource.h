#ifndef REPOSITORY_DATASOURCE_H
#define REPOSITORY_DATASOURCE_H

#include <memory>
#include <string>

namespace Repository
{
    class NodeData
    {
    public:
        virtual std::string id() = 0; // This MUST be unique for each node
        virtual unsigned int parentCount() = 0;
        virtual std::string parent(unsigned int aParent) = 0;
    };

    class DataSource
    {
    public:
        virtual ~DataSource() { }

        virtual std::string getNextId() = 0;
        virtual std::shared_ptr<NodeData> getNode(const std::string& aId) = 0;
    }; // class DataSource

} // namespace Repository

#endif // REPOSITORY_DATASOURCE_H
