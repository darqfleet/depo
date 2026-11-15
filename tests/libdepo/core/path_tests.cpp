#include <gtest/gtest.h>
#include "depo.h"
using namespace depo::core;
const std::string defaultPath{"/depo/0000/workflow"};

TEST(Path, ExtraSlashes) {
    Path path{"/extra/slash////"};
    EXPECT_EQ(path.unexpandedString(), "/extra/slash");
    path /= " ///subdir// ";
    EXPECT_EQ(path.unexpandedString(), "/extra/slash/subdir");
    Path path2{"/collect/"};
    EXPECT_EQ(path2.unexpandedString(), "/collect");
    path+=path2;
    EXPECT_EQ(path.unexpandedString(), "/extra/slash/subdir/collect");
    path += "_back";
    EXPECT_EQ(path.unexpandedString(), "/extra/slash/subdir/collect_back");
    Path path3{Path{"/root/"} + "s"};
    EXPECT_EQ(path3.unexpandedString(), "/roots");
    Path path4{Path{"/roots"} / "/config/"};
    EXPECT_EQ(path4.unexpandedString(), "/roots/config");
    Path path5{Path{"/roots//// "} / Path{"config/ "}};
    EXPECT_EQ(path5.unexpandedString(), "/roots/config");




}

TEST(Path, OperatorDivideEQ) {
    Path path{defaultPath};
    path /= "subfolder";
    EXPECT_EQ(path.unexpandedString(), "/depo/0000/workflow/subfolder");
    Path path2{"file.txt"};
    path /= path2;
    EXPECT_EQ(path.unexpandedString(), "/depo/0000/workflow/subfolder/file.txt");
    Path path3{"/root"};
    Path path4{path3 /= "config.dp"};
    EXPECT_EQ(path4.unexpandedString(), "/root/config.dp");
    EXPECT_EQ(path3.unexpandedString(), "/root/config.dp");
}

TEST(Path, operatorBool) {
    Path path{defaultPath};
    bool result{static_cast<bool>(path)};
    EXPECT_TRUE(path);
    EXPECT_TRUE(result);
    path.clear();
    EXPECT_FALSE(path);
}

TEST(Path, clear) {
    Path path{defaultPath};
    EXPECT_EQ(path.unexpandedString(), "/depo/0000/workflow");
    path.clear();
    EXPECT_EQ(path.unexpandedString(), "");
}

TEST(Path, OperatorDivide) {
    Path path{"/root"};
    Path path2 = path / "config.dp";
    EXPECT_EQ(path2.unexpandedString(), "/root/config.dp");
    Path path3{Path{"/etc"} / Path{"config.dp"}};
    EXPECT_EQ(path3.unexpandedString(), "/etc/config.dp");
    path = path / Path{"etc"} / "file.txt";
    EXPECT_EQ(path.unexpandedString(), "/root/etc/file.txt");
}


TEST(Path, OperatorPlus) {
    Path path{Path{"/a"} + Path{"/b"}};
    EXPECT_EQ(path.unexpandedString(), "/a/b");
    Path path2{Path{"/a"} + "/b2"};
    EXPECT_EQ(path2.unexpandedString(), "/a/b2");
    Path path3{"/NotChanged"};
    Path path4{path3 + path};
    EXPECT_EQ(path4.unexpandedString(), "/NotChanged/a/b");
    EXPECT_EQ(path3.unexpandedString(), "/NotChanged");

}

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

TEST(Path, CornerCase) {
    Path path{"/"};
    Path path2{"geo"};
    EXPECT_EQ(path.unexpandedString(), "/");
    path += "bin/";
    path+=path2;

    EXPECT_EQ(path.unexpandedString(), "/bingeo");
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