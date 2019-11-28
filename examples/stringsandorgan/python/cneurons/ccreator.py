#!/usr/bin/env python3

class ccreator:
    def __init__(self, baseName, path=""):
        self.baseName=str(baseName)
        self.path=str(path)
        
        self.structure = {
            "interface": {
                "defines" : [],
                "variables": []
            },
            "implementation" : {
                "defines" : [],
                "variables": []
            }
        }

    def hFileHead (self):
        header ="/*\n"
        header +=" * @file "+self.baseName.lower()+".h\n"
        header += " * @author ccreator.py a sub library of Cneurons\n"
        header += " */\n\n"
        return header + "#ifndef "+self.baseName.upper()+"_H\n#define "+self.baseName.upper() +"_H\n\n\n"
    
    def hFileFoot (self):
        return "#endif /* "+self.baseName.upper()+"_H */\n"

    def addIDef (self, defLine):
        self.structure['interface']['defines'].append (defLine)
    
    def addIVar (self, var):
        '''
        example:
        {"name":"ff_stringssamples",
            "type":"float",
            "data":list(strings[len(strings)-1])
            }
        '''
        try:
            if type (var['data']) is list:
                lengthdef=str(var['name']+"_CONST").upper()
                self.addIDef(lengthdef + " ("+str(len(var['data']))+"u)")
                var['size']=lengthdef
                
            self.structure['interface']['variables'].append (var)
            
        except Exception as e:
            print (e)
            return False
    

    def _list2cArray(self, arr):
        arrstr = arr['type'] + " " + arr['name'] + "["+arr['size']+"] = {\n"
        
        first=True
        for d in arr['data']:
            if not first:
                arrstr += ",\n"
            else:
                first = False
            arrstr += "    "+str(d)+""
            
        
        arrstr += "};\n\n"
        return arrstr
    
    
    def _defines(self, deflist):
        deftxt = ""
        for d in deflist:
            deftxt += "#define "+d+"\n"
            
        deftxt += "\n"
        
        header = '''/******************************************************************************
 * Defines                                                                    *
 ******************************************************************************/\n\n'''
        return header+deftxt
    
    def create (self):
        print ("\nCreating "+self.path + self.baseName+".h ...")
        if 'interface' in self.structure:
            file = open(self.path + self.baseName+".h", "w")

            try:
                file.write(self.hFileHead())
                file.write(self._defines(self.structure['interface']['defines']))
                
                if 'variables' in self.structure['interface']:
                    print ("Variables found in interface.")
                    for var in self.structure['interface']['variables']:
                        print ("Writing filescope variables.")
                        #print (var)
                        if type (var['data']) is list:
                            print ("...writing %s" % str(var['name']))
                            file.write (self._list2cArray(var))
                                
                                
            except Exception as e:
                print ("\nERROR: Could not export from ccreator\n")
                print (str(e))
            
            file.write(self.hFileFoot())
            file.close()
            
        else:
            
            pass
        

    
