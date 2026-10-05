class QTipUikit < Formula
  desc "A mod for Q-Tip that provides UI"
  homepage "https://github.com/ProPythonCoderAya/homebrew-q-tip-uikit"
  url "https://github.com/ProPythonCoderAya/homebrew-q-tip-uikit/archive/refs/tags/v0.0.2.tar.gz"
  head "https://github.com/ProPythonCoderAya/homebrew-q-tip-uikit.git", branch: "main"
  sha256 "d2d072b0df043c112816888d121eb58cdcbce89a07a83c3b3150c56a65a0bdbf"
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