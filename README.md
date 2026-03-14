# Random Sentence Generator using Context-free Grammars

## Current CFG

This will change as the project grows. Terminals are highlighted with brackets ("[]") around them.

```
Sentence -> SimpleSentence

ComplexSentence -> DepClause [,] IndepClause | IndepClause DepClause

IndepClause -> SimpleSentence

Dep Clause -> [conjunction] SimpleSentence

SimpleSentence -> Subject Verb

Subject -> [article] [noun] | [noun] 

Verb -> [adverb] Verb | [verb]
```

Note: for Subject, we can include Subject [and] Subject could be implemented, as well as an Object non-terminal, but we ran out of time