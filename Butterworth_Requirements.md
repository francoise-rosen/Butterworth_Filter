# Butterworth Filter Requirements and Tasks
## Functionality
1. LPF (2 - 10 order)
2. HPF (2 - 10 order)
3. BPF (2, 4, 6, 8, 10, 12 order)

## Parameters / Controls
1. Cutoff Frequency
2. Order
3. Filter Type

## Cascade implementation notes
Implement as Graph where Verticies are filter types (Biquads)
- add all vertices (max 6 (or 12 for BPF?)) upon initialisation
- connected verticies via choosing FilterType and Order. 
