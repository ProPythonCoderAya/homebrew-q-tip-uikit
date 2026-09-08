class QTipUIKit < Formula
  desc "A simple C++ graphics framework"
  homepage "https://github.com/ProPythonCoderAya/Q-Tip"
  url "https://github.com/ProPythonCoderAya/Q-Tip/archive/refs/tags/v0.1.5.tar.gz"
  head "https://github.com/ProPythonCoderAya/Q-Tip.git", branch: "main"
  sha256 "7e99b1aec9e1a9334c4bd4aba6519abed61c9627881f4faeeb2a9992725f3fe8"
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