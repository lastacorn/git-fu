#ifndef REPOSITORY_REPOSITORY_H
#define REPOSITORY_REPOSITORY_H

#include "datasource.h"
#include <memory>

namespace Repository
{
    class Repository
    {
    public:
        Repository(std::shared_ptr<DataSource> aDataSource);
        virtual ~Repository();

    private:
        std::shared_ptr<DataSource> mDataSource;
    }; // class Repository

} // namespace Repository

#endif // REPOSITORY_REPOSITORY_H
