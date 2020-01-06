#!/bin/sh
for sample in Summer16MiniAODv3.WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph Summer16MiniAODv3.WGJets_MonoPhoton_PtG-130_TuneCUETP8M1_13TeV-madgraph Summer16MiniAODv3.WJetsToLNu_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8 Summer16MiniAODv3.WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8 Summer16MiniAODv3.WJetsToLNu_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8 Summer16MiniAODv3.WJetsToLNu_HT-600To800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8 Summer16MiniAODv3.WJetsToLNu_HT-800To1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8 Summer16MiniAODv3.WJetsToLNu_HT-1200To2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8 Summer16MiniAODv3.WJetsToLNu_HT-2500ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8 Summer16MiniAODv3.TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8 Summer16MiniAODv3.TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8 Summer16MiniAODv3.TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8 Summer16MiniAODv3.TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8 Summer16MiniAODv3.TTJets_HT-600to800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8 Summer16MiniAODv3.TTJets_HT-800to1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8 Summer16MiniAODv3.TTJets_HT-1200to2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8 Summer16MiniAODv3.TTJets_HT-2500toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8 Summer16MiniAODv3.TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8 Summer16MiniAODv3.GJets_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8 Summer16MiniAODv3.GJets_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8 Summer16MiniAODv3.GJets_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8 Summer16MiniAODv3.GJets_HT-600ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8 Summer16MiniAODv3.QCD_HT200to300_TuneCUETP8M1_13TeV-madgraphMLM-pythia8 Summer16MiniAODv3.QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8 Summer16MiniAODv3.QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8 Summer16MiniAODv3.QCD_HT700to1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8 Summer16MiniAODv3.QCD_HT1000to1500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8 Summer16MiniAODv3.QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8 Summer16MiniAODv3.QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8 Summer16MiniAODv3.ZJetsToNuNu_HT-100To200_13TeV-madgraph Summer16MiniAODv3.ZJetsToNuNu_HT-200To400_13TeV-madgraph Summer16MiniAODv3.ZJetsToNuNu_HT-400To600_13TeV-madgraph Summer16MiniAODv3.ZJetsToNuNu_HT-600To800_13TeV-madgraph Summer16MiniAODv3.ZJetsToNuNu_HT-800To1200_13TeV-madgraph Summer16MiniAODv3.ZJetsToNuNu_HT-1200To2500_13TeV-madgraph Summer16MiniAODv3.ZJetsToNuNu_HT-2500ToInf_13TeV-madgraph Summer16MiniAODv3.ZGTo2NuG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8

do
    echo "grep $sample inputFiles.txt_main > $sample.txt"
    grep $sample /uscms/home/vhegde/inputFileList_V16.txt > $sample.txt
#    echo "$sample "
#    ls /eos/uscms/store/user/lpcsusyhad/SusyRA2Analysis2015/Run2ProductionV12/$sample*.root -l | wc -l
done
