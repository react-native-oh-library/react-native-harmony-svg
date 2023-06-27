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

  addAttribute(name: string, value: string | number) {
    this.attributeValueByName[name] = value
    return this;
  }

  addAttributes(attributes: Object) {
    for (const [name, value] of Object.entries(attributes)) {
      this.attributeValueByName[name] = value
    }
    return this;
  }

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