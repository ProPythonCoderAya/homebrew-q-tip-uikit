class QTipUikit < Formula
  desc "A mod for Q-Tip that provides UI"
  homepage "https://github.com/ProPythonCoderAya/homebrew-q-tip-uikit"
  url "NaN"
  head "https://github.com/ProPythonCoderAya/homebrew-q-tip-uikit.git", branch: "main"
  sha256 "NaN"
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