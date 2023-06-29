export class XMLElementBuilder {
  tag: string | undefined
  children: string | undefined;
  attributeValueByName: Record<string, string | number> = {}
  parserByAttributeName: Record<string, (value: any) => string> = {}

  setTag(tag: string) {
    this.tag = tag
    return this;
  }

  addCustomParser(attributeName: string, parser: (value: any) => string) {
    this.parserByAttributeName[attributeName] = parser
    return this;
  }

  addChildren(children: string) {
    this.children = children
    return this;
  }

  addAttributes(attributes: Object, kebabize: boolean = false) {
    for (const [name, value] of Object.entries(attributes)) {
      this.addAttribute(name, value, kebabize)
    }
    return this;
  }

  addAttribute(name: string, value: string | number | undefined, kebabize: boolean = false) {
    const key = kebabize ? this.kebabize(name) : name
    if (value === undefined) {
      delete this.attributeValueByName[key]
      return;
    }
    this.attributeValueByName[key] = value
    return this;
  }

  private kebabize = (str: string) => str.replace(/[A-Z]+(?![a-z])|[A-Z]/g, ($, ofs) => (ofs ? "-" : "") + $.toLowerCase())

  build(): string {
    if (!this.tag) {
      throw new Error("Tag must be set.")
    }

    if (this.children) {
      return `<${this.tag} ${this.buildAttributes()}>${this.children}</${this.tag}>`
    }
    return `<${this.tag} ${this.buildAttributes()} />`
  }

  private buildAttributes() {
    return Object.entries(this.attributeValueByName).reduce((acc, [key, value]) => {
      const parsedValue = this.parserByAttributeName[key] ? this.parserByAttributeName[key](value) : value.toString()
      acc += ` ${key}="${parsedValue}"`
      return acc
    }, "")
  }
}