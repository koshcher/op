import { markdown } from "../lib"

export default {
  load() {
    const code = markdown('```cpp\nstd::cout << "Bullshit";\n```')
    return code
  },
}
