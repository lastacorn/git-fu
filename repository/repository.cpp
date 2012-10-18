#include "repository.h"

namespace Repository
{
    Repository::Repository(std::shared_ptr<DataSource> aDataSource)
    {
        aDataSource->getNextId();
    }
    
    Repository::~Repository()
    {
    }
}