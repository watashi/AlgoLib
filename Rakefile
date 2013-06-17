require 'rake'
require 'rake/clean'

BIN = 't/gtest'
SRC = 't/gtest.cc'
INC = 't/'

CXX = 'g++'
CXXFLAGS = '-std=c++11 -O2 -Wall -Wextra -Wconversion'

CLEAN.include('*.o')

rule '.o' => '.cc' do |t|
  inc = File.join(Dir.pwd, INC)
  sh "#{CXX} -I#{inc} #{CXXFLAGS} -c -o #{t.name} #{t.source}"
end

task :default => [:test]

task :test do
  dir = Rake.original_dir
  src = `find "#{dir}" -wholename '*GTest.cc'`.lines.map(&:chomp)
  src << File.join(Dir.pwd, SRC)
  obj = src.map{|i| i.ext('.o')}
  file BIN => obj do
    sh "#{CXX} -lgtest -o #{BIN} #{obj * ' '}"
  end
  Rake::Task[BIN.to_sym].invoke
  sh "ulimit -s unlimited && ./#{BIN}"
end
