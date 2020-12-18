
## patch failed
- st-openclipboard-20190202-0.8.1.diff
```
 void
 xunloadfont(Font *f)
 {
@@ -1057,6 +1155,9 @@ xinit(int cols, int rows)
 	usedfont = (opt_font == NULL)? font : opt_font;
 	xloadfonts(usedfont, 0);

+	/* spare fonts */
+	xloadsparefonts();
+
 	/* colors */
 	xw.cmap = XDefaultColormap(xw.dpy, xw.scr);
 	xloadcols();

```
