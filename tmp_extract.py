from pathlib import Path
text = Path('maps/view-source_https___intranet.42heilbronn.de_floor-plans_og.html').read_text(errors='ignore')
print('len', len(text))
for k in ['floorPlans', 'svg_content', 'initialViewSlug', 'furnitureGroups', 'rooms', 'clusters']:
    print(k, text.count(k))
idx = text.find('floorPlans')
print('idx_floorPlans', idx)
if idx != -1:
    print(text[idx:idx+1500])
