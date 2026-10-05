class QTipUikit < Formula
  desc "A mod for Q-Tip that provides UI"
  homepage "https://github.com/ProPythonCoderAya/homebrew-q-tip-uikit"
  url "https://github.com/ProPythonCoderAya/homebrew-q-tip-uikit/archive/refs/tags/v0.0.1.tar.gz"
  head "https://github.com/ProPythonCoderAya/homebrew-q-tip-uikit.git", branch: "main"
  sha256 "e7f3f0f231716277b76a3fbaff2020c040df4721e96e022b05da6dcead84fd45"
  license "MIT"

  depends_on "cmake"
  depends_on "magic_enum"
  depends_on "propythoncoderaya/q-tip/q-tip"

  def install
    system "cmake", "-S", ".", "-B", "build",
            "-DCMAKE_BUILD_TYPE=Release",
           *std_cmake_args

    system "cmake", "--build", "build"

    system "cmake", "--install", "build"
  end
end