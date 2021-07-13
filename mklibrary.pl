#!/usr/bin/perl

print "char* librarysrc[] = {\n";
while (<>) {
  chomp;
  print "  \"$_\",\n";
  }
print "  \"__END__\"\n";
print "  };\n";

