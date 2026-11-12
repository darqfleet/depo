struct BuildInfo {
    static inline const std::string commit_sha{"@GIT_COMMIT_SHA@"};
    static inline const std::string timestamp{"@TIMESTAMP@"};
    static inline const std::string version{"@PROJECT_VERSION@"};
};