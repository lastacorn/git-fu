#include "gitfu.h"
#include <QtGui/QApplication>

#include <git2.h>

#include <stdio.h>
#include "gitfu-version.h"

int main(int argc, char *argv[])
{
    // TODO: Move this to an about page
    printf("git-fu version %s\n", GITFU_VERSION_STR);

    const char* path = "D:\\git\\test-repositories\\sample1";
    git_repository *repo = NULL;
    int rc = git_repository_open(&repo, path);
    printf("Open repo %s returned %d", path, rc);

    QApplication a(argc, argv);
    GitFu w;
    w.show();
    return a.exec();
}
