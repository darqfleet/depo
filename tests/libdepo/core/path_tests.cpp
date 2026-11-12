#include <gtest/gtest.h>
#include "path.h"
using namespace depo::core;
const std::string defaultPath{"/depo/0000/workflow"};

TEST(Path, OperatorPLusEQ) {
    Path path{defaultPath};
    path += Path{"/added"};
    EXPECT_EQ(path.unexpandedString(), "/depo/0000/workflow/added");
    path += "/subdir";
    EXPECT_EQ(path.unexpandedString(), "/depo/0000/workflow/added/subdir");
}

TEST(Path, OperatorEQ) {
    Path path{defaultPath};
    Path path2{"/other/path"};
    bool result_f{path == path2};
    bool result_t{path != path2};
    EXPECT_FALSE(result_f);
    EXPECT_TRUE(result_t);
    EXPECT_EQ(path, Path{defaultPath});
    EXPECT_FALSE(path == Path{"/other/path"});
    EXPECT_TRUE(path2 == Path{"/other/path"});
    EXPECT_FALSE(Path{defaultPath} == "/other/path");
    EXPECT_TRUE(path == "/depo/0000/workflow");

}

TEST(Path, CtorRValue) {
    Path path{defaultPath};
    ASSERT_EQ(path.unexpandedString(), defaultPath);
}

TEST(Path, CopyCtor) {
    Path path{defaultPath};
    Path path_copy{path};
    ASSERT_EQ(path.unexpandedString(), path_copy.unexpandedString());
}

TEST(Path, CopyAssignmentCtor) {
    Path path{defaultPath};
    Path path_copy;
    path_copy = path;
    ASSERT_EQ(path.unexpandedString(), path_copy.unexpandedString());
}

TEST(Path, moveCtor) {
    Path path{defaultPath};
    Path path2{std::move(path)};
    ASSERT_EQ(path.unexpandedString(), "");
    ASSERT_EQ(path2.unexpandedString(), defaultPath);
}

TEST(Path, moveCtorSelf) {
    Path path{defaultPath};
    path = std::move(path);
    EXPECT_EQ(path.unexpandedString(), defaultPath);
}

TEST(Path, moveAssingnmentOperator) {
    Path path{defaultPath};
    Path path2;
    path2 = std::move(path);
    ASSERT_EQ(path.unexpandedString(), "");
    ASSERT_EQ(path2.unexpandedString(), defaultPath);
}

int main(int argc, char **argv) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}