[1mdiff --git a/.gitignore b/.gitignore[m
[1mindex 7ea83f5..9e1006c 100644[m
[1m--- a/.gitignore[m
[1m+++ b/.gitignore[m
[36m@@ -3,6 +3,8 @@[m [mlib/*[m
 [m
 bin/*[m
 [m
[32m+[m[32m*.obj[m
[32m+[m
 //Visual studio stuff[m
 *.opensdf[m
 *.sdf[m
[36m@@ -11,5 +13,10 @@[m [mbin/*[m
 *.vcxproj[m
 *.filters[m
 *.user[m
[32m+[m[32m*.tlog[m
[32m+[m[32m*.log[m
[32m+[m[32m*.idb[m
[32m+[m[32m*.pdb[m
[32m+[m
[32m+[m[32mDebug/[m
 [m
[31m-Debug/[m
\ No newline at end of file[m
[1mdiff --git a/test/test2.json b/test/test2.json[m
[1mindex 229cccd..a0c407c 100644[m
[1m--- a/test/test2.json[m
[1m+++ b/test/test2.json[m
[36m@@ -1,9 +1,9 @@[m
 [m
 {[m
[32m+[m	[32m"aKey" : "Stuff",[m
 	"jdsakfjdsa" : {[m
 		"sdafdsa" : [[m
 			15,2,3[m
 		][m
[31m-	},[m
[31m-	"Key" : "Stuff"[m
[32m+[m	[32m}[m
 }[m
\ No newline at end of file[m
