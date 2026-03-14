# Random Sentence Generator using Context-free Grammars

## Current CFG

This will change as the project grows. Terminals are highlighted with brackets ("[]") around them.

```
Complex Sentence -> DepClause IndepClause

IndepClause -> Sentence

Dep Clause -> [conjunction] Sentence

Sentence -> Subject Verb

Subject -> [article] [noun] | [noun]

Verb -> [adverb] Verb | [verb]
```