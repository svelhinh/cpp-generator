# cpp-generator

cpp-generator can create classes with Coplien's form.<br />
Do a make to compile.<br />

### Class Generator : <br />
Create Default Class : ./cpp-generator<br />
Create Custom Class : ./cpp-generator -f [Class Name]<br />
./cpp-generator -f [Class Name] [Class Name 2] [Class Name 3]<br /><br />

### Template Class Generator : <br />
Same as the class generator with option -t <br /><br />

### Getters/Setters Generator : <br />
./cpp-generator -gs [Class Name]<br />
./cpp-generator -gs [Class Name] [Class Name 2] [Class Name 3]<br />
You have a Test class if you want to test this<br /><br /><br />

### Known bugs : <br />
- private attributes before public with one or more empty lines between attributes causes a Segmentation Fault
