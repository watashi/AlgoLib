require 'rake'
require 'rake/clean'

BIN = 't/gtest_main'
SRC = %w(t/gtest_main.cc t/gtest-all.cc)
INC = File.join(Dir.pwd, 't/')

CXX = 'g++'
CXXFLAGS = '-std=c++11 -O2 -Wall -Wextra -Wconversion -D_GLIBCXX_DEBUG'

CLEAN.include('**/*.o')
CLOBBER.include(BIN)

rule '.o' => '.cc' do |t|
  sh "#{CXX} -I#{INC} #{CXXFLAGS} -c -o #{t.name} #{t.source}"
end

task :default => [:test]

task :testbin do
  dir = Rake.original_dir
  src = `find "#{dir}" -wholename '*GTest.cc'`.lines.map(&:chomp)
  src += SRC.map{|i| File.join(Dir.pwd, i)}
  obj = src.map{|i| i.ext('.o')}
  file BIN => obj do
    sh "#{CXX} -lpthread -o #{BIN} #{obj * ' '}"
  end
  Rake::Task[BIN.to_sym].invoke
end

task :test => :testbin do
  sh "ulimit -s unlimited && ./#{BIN} --gtest_shuffle"
end
