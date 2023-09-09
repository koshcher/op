import { createMarkdownRenderer } from "vitepress"

const config = globalThis.VITEPRESS_CONFIG.srcDir
const md = await createMarkdownRenderer(
  config.srcDir,
  config.markdown,
  undefined,
  // config.site.base ,
  config.logger
)

/** @param {string} str */
export function markdown(str) {
  return md.render(str)
}
