class TextJustification {
    public static List<String> fullJustify(String[] words, int maxWidth) {
        ArrayList<ArrayList<String>> wrappedText = new ArrayList();
        int currentLineWidth = 0;
        ArrayList<String> lastLine = new ArrayList();
        ArrayList<Integer> lineWidth = new ArrayList();
        for(String word : words) {
            if(currentLineWidth + word.length() <= maxWidth) {
                currentLineWidth += word.length() + 1;
                lastLine.add(word);
            } else {
                wrappedText.add(lastLine);
                lineWidth.add(currentLineWidth - 1);
                lastLine = new ArrayList();
                lastLine.add(word);
                currentLineWidth = word.length() + 1;
            }
        }   
        wrappedText.add(lastLine);
        lineWidth.add(currentLineWidth - 1 > 0 ? currentLineWidth - 1  : 0);
        ArrayList<String> result = new ArrayList();
        /* no justification with last line */
        for(int i = 0; i < wrappedText.size() - 1; i++) { 
            ArrayList<String> line = wrappedText.get(i);
            String justifiedLine = "";
            int numberOfSpace = line.size() - 1;
            // this excludes one spacebar that must have between words
            int totalSpaceWidth = maxWidth - lineWidth.get(i);
            if(numberOfSpace == 0) {
                String s = line.get(0);
                s += new String(new char[maxWidth - s.length()]).replace('\0', ' ');
                result.add(s);
                continue;
            }
            int m = totalSpaceWidth / numberOfSpace;
            int n = totalSpaceWidth % numberOfSpace;
            for(int j = 0; j < line.size(); j++) {
                int v = j < n ? m + 1 : m;
                String space = j != line.size() - 1 ? new String(new char[v + 1]).replace('\0', ' ') : "";
                justifiedLine += line.get(j) + space;
            }
            result.add(justifiedLine);
        }
        if(wrappedText.size() > 0) {
            ArrayList<String> line = wrappedText.get(wrappedText.size() - 1);
            String s = "";
            for(String word : line) {
                s += word + " ";
            }
            s += new String(new char[maxWidth]).replace('\0', ' ');
            result.add(s.substring(0, maxWidth));
        }
        return result;
    }
}
