// Absolute path to canonical path
class PathSimplifier {
    private static boolean skip(String s) {
        return s.equals("") || s.equals(".");
    } 
    public static String simplifyPath(String path) {
        String[] splitedPath = path.split("/");
        splitedPath = Stream.of(splitedPath).filter(s -> !skip(s)).toArray(String[]::new);
        String result = "";
        int jump = 0;
        for(int i = splitedPath.length - 1; i >= 0; i--) {
            String s = splitedPath[i];
            if(s.equals("..")) {
                jump++;
            } else {
                if(jump > 0) {
                    jump -= 1;
                    continue;
                }
                result = "/" + s + result;
            }
        }
        if(result.equals("")) return "/";
        return result;
    }
}
