Pod::Spec.new do |s|

  s.name         = "CSVKit2"
  s.version      = "0.0.3"
  s.summary      = "A Comma-Separated Value (CSV) format parser for Objective-C."

  s.description  = <<-DESC
CSVKit provides block-based CSV parsers for Objective-C. The internal parsing routines are written in C for speed (and are largely adapted from Python's csv module). The parser calls user-supplied blocks as it incrementally parses the source data.
                   DESC

  s.homepage     = "https://github.com/kzim44/CSVKit"
  s.license      = 'MIT'


  s.author       = { "Kevin" => "kevin@kevinz.com" }
  s.source       = { :git => "https://github.com/kzim44/CSVKit.git", :tag => "0.0.3" }

  s.requires_arc = true
  s.source_files  = 'CSVKit2/**/*.{h,m}'

end
