{
  description = "depo - like experimental assets manager";

  inputs = {
    nixpkgs.url = "https://channels.nixos.org/nixos-unstable/nixexprs.tar.zst";
    houdini = {
      url = "github:permahorse/houdini-nix";
      inputs.nixpkgs.follows = "nixpkgs";
    };
  };

  outputs = { self, nixpkgs, houdini }:
  let
    system = "x86_64-linux";
    pkgs = import nixpkgs { config.allowUnfree = true; inherit system; };
    target-houdini = houdini.packages.${system}.houdini-22_0_368;
  in {
    packages.${system} = {
      houmod = target-houdini.override (
        super: { extraFhsPkgs = pkgs: (super.extraFhsPkgs pkgs) ++ [

        #nativeBuildInputs
          pkgs.git
          pkgs.which
#          pkgs.gcc-unwrapped
          pkgs.gcc
          pkgs.cmake
          pkgs.ninja
          pkgs.gtest.dev
          pkgs.gtest
          pkgs.clang-tools
          pkgs.cppcheck
          pkgs.valgrind
          pkgs.lcov
          pkgs.gcovr
#          pkgs.glibc.dev
#          pkgs.glibc

        #buildInputs
          target-houdini.unwrapped
          pkgs.mongocxx
          pkgs.mongoc
          pkgs.openssl
          pkgs.openssl.dev
          pkgs.cyrus_sasl
          pkgs.cyrus_sasl.dev
        ]; }
      );

      devShellHDK = pkgs.writeShellScriptBin "HoudiniDevShell" ''
          export HFS=${self.packages.${system}.houmod.unwrapped};
          export BLA=${pkgs.openssl.dev};
          cd $HFS
          source houdini_setup
          export HOUDINI_DSO_ERROR=2
          export HOUDINI_NO_SPLASH=1
          export HOUDINI_OCL_DEVICETYPE=CPU
          exec ${self.packages.${system}.houmod}/bin/houdini-22.0.368 ${pkgs.bash}/bin/bash "$@"
        '';
    };
  };
}

