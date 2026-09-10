class QTipUikit < Formula
  desc "A mod for Q-Tip that provides UI"
  homepage "https://github.com/ProPythonCoderAya/homebrew-q-tip-uikit"
  url "https://github.com/ProPythonCoderAya/homebrew-q-tip-uikit/archive/refs/tags/v0.0.0.tar.gz"
  head "https://github.com/ProPythonCoderAya/homebrew-q-tip-uikit.git", branch: "main"
  sha256 "7fd16478f499677b58c075e4f7cfbf157dfc577defbd577fad8894e7f22ee5e7"
  license "MIT"

  depends_on "cmake"
  depends_on "q-tip"

  def install
    system "cmake", "-S", ".", "-B", "build",
            "-DCMAKE_BUILD_TYPE=Release",
           *std_cmake_args

    system "cmake", "--build", "build"

    system "cmake", "--install", "build"
  end
end