require 'rake'
require 'rake/clean'

BIN = 't/gtest_main'
SRC = %w(t/gtest/gtest_main.cc t/gtest/gtest-all.cc)
INC = File.join(Dir.pwd, 't/')

CXX = ENV['CXX'] || 'g++'
CXXFLAGS = '-std=c++0x -O2 -Wall -Wextra -Wconversion'
CXXFLAGS << ' -D_GLIBCXX_DEBUG' unless ENV['NO_GLIBCXX_DEBUG']

CLEAN.include('**/*.o')
CLOBBER.include(BIN)

rule '.o' => '.cc' do |t|
  sh "#{CXX} -I#{INC} #{CXXFLAGS} -c -o #{t.name} #{t.source}"
end

task :default => [:test]

task :build do
  dir = Rake.original_dir
  src = `find "#{dir}" -wholename '*GTest.cc'`.lines.map(&:chomp)
  src.each do |i|
    dep = []
    dep << "GTestHelper.cpp"
    dep << "../#{$1}.cpp" if i =~ /(\w+)GTest.cc$/
    dep = dep.map{|j| File.join(File.dirname(i), j)}
    dep = dep.select{|j| File.exists? j}
    dep << i
    file i.ext('.o') => dep
  end

  src += SRC.map{|i| File.join(Dir.pwd, i)}
  obj = src.map{|i| i.ext('.o')}
  file BIN => obj do
    sh "#{CXX} -lpthread -o #{BIN} #{obj * ' '}"
  end
  Rake::Task[BIN.to_sym].invoke
end

task :test => :build do
  sh "ulimit -s unlimited && ./#{BIN} --gtest_shuffle"
end
