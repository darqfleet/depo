#include <gtest/gtest.h>
#include "path.h"
using namespace depo::core;

TEST(Path, CtorRValue) {
    Path path{"/depo/0000/workflow"};
    ASSERT_EQ(path.evalAsString(), "/depo/0000/workflow");
}

TEST(Path, CopyCtor) {
    Path path{"/depo/0000/workflow"};
    Path path_copy{path};
    ASSERT_EQ(path.evalAsString(), path_copy.evalAsString());
}

TEST(Path, CopyAssignmentCtor) {
    Path path{"/depo/0000/workflow"};
    Path path_copy;
    path_copy = path;
    ASSERT_EQ(path.evalAsString(), path_copy.evalAsString());
}

TEST(Path, moveCtor) {
    Path path{"/depo/0000/workflow"};
    Path path2{std::move(path)};
    ASSERT_EQ(path.evalAsString(), "");
    ASSERT_EQ(path2.evalAsString(), "/depo/0000/workflow");
}

TEST(Path, moveAssingnmentOperator) {
    Path path{"/depo/0000/workflow"};
    Path path2;
    path2 = std::move(path);
    ASSERT_EQ(path.evalAsString(), "");
    ASSERT_EQ(path2.evalAsString(), "/depo/0000/workflow");
}

int main(int argc, char **argv) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}