import { markdown } from "../lib"

export default {
  load() {
    const code = markdown('```cpp\nstd::cout << "Bullshit";\n```')
    return code
  },
}

/*
<script src="https://cdn.jsdelivr.net/npm/mermaid/dist/mermaid.min.js"></script>
<div class="mermaid">

%%{init: {'flowchart' : {'curve' : 'stepAfter'}}}%%

flowchart  TD
  A((Start))
  A --- B
  A --- C
  A --- D
  A --- E
  B --- B1
  B --- B2

  C --- B1

</div>

*/
