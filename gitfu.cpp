#include "gitfu.h"
#include "gitfu-version.h"
#include "repository/repository.h"

#include <git2.h>
#include <exception>

// Conversion to/from OID
void oidToString(const git_oid& aId, std::string& aString)
{
	char str[GIT_OID_HEXSZ+1];
    git_oid_fmt(str, &aId);
    str[GIT_OID_HEXSZ] = '\0';
    aString = str;
}
void stringToOid(const std::string& aString, git_oid& aId)
{
    git_oid_fromstr(&aId, aString.c_str());
}

class GitDataNode : public Repository::NodeData
{
public:
    GitDataNode(git_commit* aCommit)
        : mCommit(aCommit)
    {
    }

    ~GitDataNode()
    {
        git_commit_free(mCommit);
    }

    virtual std::string id()
    {
        return std::string();
    }

    virtual unsigned int parentCount()
    {
        return git_commit_parentcount(mCommit);
    }

    virtual std::string parent(unsigned int aParent)
    {
        const git_oid* parent = git_commit_parent_oid(mCommit, aParent);
        std::string parentId;
        oidToString(*parent, parentId);
        return parentId;
    }

private:
    git_commit* mCommit;
};

class GitDataSource : public Repository::DataSource
{
public:
    GitDataSource(const char* aPath)
        : mRepo(NULL)
        , mWalk(NULL)
    {
        int rc = git_repository_open(&mRepo, aPath);
        if(rc != GIT_OK)
        {
            throw std::exception("Unable to open repository");
        }
        rc = git_revwalk_new(&mWalk, mRepo);
        if(rc != GIT_OK)
        {
            throw std::exception("Unable to walk repository");
        }
        git_revwalk_sorting(mWalk, GIT_SORT_TIME /*| GIT_SORT_TOPOLOGICAL*/); // TODO: Fix libgit2 so this actually works. Right now it ignores time
        
        // TODO: Refs should be passed in as an argument
        git_strarray refs;
        rc = git_reference_list(&refs, mRepo, GIT_REF_OID);
        qDebug("Using heads:");
        for(unsigned int i = 0; i < refs.count; i++)
        {
            git_reference* ref;
            rc = git_reference_lookup(&ref, mRepo, refs.strings[i]);
            if(GIT_OK != rc)
            {
                continue;
            }
            const git_oid* ref_oid = git_reference_oid(ref);
            if(ref_oid == NULL)
            {
                // TODO: This is a bug in libgit2. Fix it.
                // refs/remotes/origin/HEAD is returned by GIT_REF_LISTALL and passes
                // reference_lookup, but sets ref to NULL. Happens on GitExtensions repo on home PC.
                continue;
            }
            git_oid oid = *ref_oid;
            rc = git_revwalk_push(mWalk, &oid);

            qDebug("\t%03d: %s", i, refs.strings[i]);
        }
    }

    ~GitDataSource()
    {
        git_repository_free(mRepo);
        git_revwalk_free(mWalk);
    }

    virtual std::string getNextId()
    {
        std::string str;
        git_oid oid;
        if(git_revwalk_next(&oid, mWalk) == GIT_OK)
        {
            oidToString(oid, str);
        }
        return str;
    }

    virtual std::shared_ptr<Repository::NodeData> getNode(const std::string& aId)
    {
        git_oid oid;
        stringToOid(aId, oid);
        git_commit* commit;
        int error = git_commit_lookup(&commit, mRepo, &oid);
        return std::shared_ptr<Repository::NodeData>(new GitDataNode(commit));
    }

private:
    git_repository* mRepo;
    git_revwalk* mWalk;
};

GitFu::GitFu(QWidget *parent, Qt::WFlags flags)
    : QMainWindow(parent, flags)
{
    ui.setupUi(this);

    // TODO: Move this to an about page
    QString title;
    title.sprintf("git-fu version %s\n", GITFU_VERSION_STR);
    setWindowTitle(title);

    std::shared_ptr<Repository::DataSource> dataSource(new GitDataSource("D:\\git\\test-repositories\\sample1"));
    Repository::Repository* r = new Repository::Repository(dataSource);
}

GitFu::~GitFu()
{

}
