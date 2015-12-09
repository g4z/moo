
str = "This is a long string ";
k = "and add this to the end";
x = 123;
y = x*20;
z = y - 20 + 5;
name = "may";
name = name + "ukh";

str = str + k;

print "Hello world ", x, " ", y;
print str;
x = 2460;
if x > y then
   print "x is greater than y";
end;
if x < y then
   print "x is less than y";
   print "x = ", x;
   print "y = ", y;
end;
if x = y then
   print "x is equal to y";
end;

if name = "mayukh" then
   print "This is mayukh";
else if name = "chris" then
   print "This is my name";
end;

print "Counting from 1 to 20";
x = 1;
while x <= 20 do
   print "x = ", x;
   y = x % 2;
   if y = 0 then
      print x, " is an even number";
   end;
   x = x + 1;
end;

print "Done counting to 20";

