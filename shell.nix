with import <mypkgs>{}; {
  ISOenv = stdenv.mkDerivation {
    name = "ISO-Engine";
    buildInputs = [sfml cmake];
  };
}
