{ pkgs, lib, config, inputs, ... }:

{
  # https://devenv.sh/packages/
  packages = with pkgs; [ 
    cmake
    just
    # See: https://github.com/NixOS/nixpkgs/blob/nixos-unstable/pkgs/development/libraries/opencv/4.x.nix#L667
    (opencv.override { enableGtk3 = true; })
    ninja
    gtk2
  ];

  # https://devenv.sh/languages/
  languages.cplusplus.enable = true;

  # See full reference at https://devenv.sh/reference/options/
}
