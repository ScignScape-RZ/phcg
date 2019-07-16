#!/usr/bin/env groovy
@Grab(group='de.tudarmstadt.ukp.dkpro.core', version='1.9.3',
      module='de.tudarmstadt.ukp.dkpro.core.opennlp-asl')
import de.tudarmstadt.ukp.dkpro.core.opennlp.*;
@Grab(group='de.tudarmstadt.ukp.dkpro.core', version='1.9.3',
      module='de.tudarmstadt.ukp.dkpro.core.languagetool-asl')
import de.tudarmstadt.ukp.dkpro.core.languagetool.*;
@Grab(group='de.tudarmstadt.ukp.dkpro.core', version='1.9.3',
      module='de.tudarmstadt.ukp.dkpro.core.io.text-asl')
import de.tudarmstadt.ukp.dkpro.core.io.text.*;
@Grab(group='de.tudarmstadt.ukp.dkpro.core', version='1.9.3',
      module='de.tudarmstadt.ukp.dkpro.core.io.conll-asl')
import de.tudarmstadt.ukp.dkpro.core.io.conll.*;

import static org.apache.uima.fit.pipeline.SimplePipeline.*;
import static org.apache.uima.fit.factory.AnalysisEngineFactory.*;
import static org.apache.uima.fit.factory.CollectionReaderFactory.*;

runPipeline(
  createReaderDescription(TextReader,
    TextReader.PARAM_SOURCE_LOCATION, "g.txt",
    TextReader.PARAM_LANGUAGE, "en"),
  createEngineDescription(OpenNlpSegmenter),
  createEngineDescription(OpenNlpPosTagger),
  createEngineDescription(LanguageToolLemmatizer),
  createEngineDescription(ConllUWriter,
    ConllUWriter.PARAM_TARGET_LOCATION, "./Uout")
);

